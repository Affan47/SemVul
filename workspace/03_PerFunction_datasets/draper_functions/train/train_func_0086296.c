fsp_add_backend (fsp_link *link, const char *addr, uint16_t port, int segments)
{
  if (link->segments && link->segments != segments) {
    return 0;
  }

  int count = 0;

  int sock = fsp_open_socket(link, addr, port);
  if (sock == -1) return 0;


  int server = link->servers++;
  link->addrs[server] = g_strdup(addr);
  link->ports[server] = port;
  link->segments = segments;

  unsigned char *out = message_new(FS_NODE_SEGMENTS, 0, 0);
  write(sock, out, FS_HEADER);
  free(out);

  unsigned char *in = segment_list(link, server, sock);


  if (!in) return 0;

  for (fs_segment seg = 0; seg < link->segments; ++seg) {
    unsigned char status = in[FS_HEADER + seg];
    switch (status) {
      case 'p':
        if (link->socks1[seg] != -1) {
          continue;
        } else if (sock == -1) {
          sock = fsp_open_socket(link, link->addrs[server], link->ports[server]);
        }

        if (choose_segment(link, sock, server, seg)) break;
        link->groups[seg]= server;
        link->socks[seg] = link->socks1[seg] = sock;
        sock = -1;
        count++;
        break;
      case 'm':
        if (link->socks2[seg] != -1) {
          continue;
        } else if (sock == -1) {
          sock = fsp_open_socket(link, link->addrs[server], link->ports[server]);
        }
        if (choose_segment(link, sock, server, seg)) break;
        link->socks2[seg] = sock;
        sock = -1;
        break;
      case '\0':

        break;
      default:
        link_error(LOG_ERR, "unknown status ignored for segment %d on %s port %d",
                 seg, link->addrs[server], link->ports[server]);
        break;
    }
  }

  free(in);
  if (sock != -1) {
    close(sock);
  }

  return count;
}
