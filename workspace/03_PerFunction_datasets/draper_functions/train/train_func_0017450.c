segment_list(fsp_link *link, int server, int sock)
{
  unsigned char expected = FS_NODE_SEGMENT_LIST;
  unsigned char *list;
  fs_segment segments;
  unsigned int length;
  unsigned char *in = message_recv(sock, &segments, &length);

  if (in && in[3] == FS_ERROR) {
    free(in);
    unsigned char *out = message_new(FS_SEGMENTS, 0, 0);
    if (write(sock, out, FS_HEADER) != FS_HEADER) {
      link_error(LOG_ERR, "write failed: %s", strerror(errno));
      free(out);
      return NULL;
    }
    expected = FS_SEGMENT_LIST;
    free(out);
    in = message_recv(sock, &segments, &length);
  }

  if (!in || in[3] != expected) {
    link_error(LOG_ERR, "segment list failed for %s port %d: %s",
               link->addrs[server], link->ports[server], invalid_response(in));
    free(in);
    return NULL;
  }

  if (link->segments && link->segments != segments) {
    link_error(LOG_WARNING, "%s port %d offers %d segments not %d",
               link->addrs[server], link->ports[server], segments, link->segments);
    free(in);
    return NULL;
  } else if (!link->segments) {
    link->segments = segments;
  }

  if (expected == FS_NODE_SEGMENT_LIST) {
    if (length != link->segments) {
      link_error(LOG_WARNING, "segment list wrong size for %s port %d",
               link->addrs[server], link->ports[server]);
      free(in);
      return NULL;
    }
    list = in;
  } else {
    list = calloc(link->segments + FS_HEADER, 1);
    for (int k = 0; k < length / 4; ++k) {
      fs_segment seg;
      memcpy(&seg, in + FS_HEADER + 4 * k, sizeof(seg));
      list[FS_HEADER + seg] = 'p';
    }
  }

  return list;
}
