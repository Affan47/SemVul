get_manpage_node (FILE_BUFFER *file_buffer, char *pagename)
{
  NODE *node;

  node = manpage_node_of_file_buffer (file_buffer, pagename);

  if (!node)
    {
      char *page;

      page = get_manpage_contents (pagename);

      if (page)
        {
          char header[1024];
          long oldsize, newsize;
          int hlen, plen;
	  char *old_contents = file_buffer->contents;

          sprintf (header, "\n\n%c\n%s %s,  %s %s,  %s (dir)\n\n",
                   INFO_COOKIE,
                   INFO_FILE_LABEL, file_buffer->filename,
                   INFO_NODE_LABEL, pagename,
                   INFO_UP_LABEL);
          oldsize = file_buffer->filesize;
          hlen = strlen (header);
          plen = strlen (page);
          newsize = (oldsize + hlen + plen);
          file_buffer->contents = xrealloc (file_buffer->contents, 1 + newsize);
          memcpy (file_buffer->contents + oldsize, header, hlen);
          memcpy (file_buffer->contents + oldsize + hlen, page, plen);
          file_buffer->contents[newsize] = '\0';
          file_buffer->filesize = newsize;
          file_buffer->finfo.st_size = newsize;
          build_tags_and_nodes (file_buffer);
          free (page);


	  if (old_contents && oldsize && old_contents != file_buffer->contents
	      && info_windows)
	    {
	      int iw;
	      INFO_WINDOW *info_win;
	      char *old_contents_end = old_contents + oldsize;

	      for (iw = 0; (info_win = info_windows[iw]); iw++)
		{
		  int in;

		  for (in = 0; in < info_win->nodes_index; in++)
		    {
		      NODE *tmp_node = info_win->nodes[in];


		      if (tmp_node && tmp_node->filename
                          && tmp_node->contents
                          && strcmp (tmp_node->filename,
				  MANPAGE_FILE_BUFFER_NAME) == 0
                          && tmp_node->contents >= old_contents
                          && tmp_node->contents + tmp_node->nodelen
                                <= old_contents_end)
			{
			  info_win->nodes[in] =
			    manpage_node_of_file_buffer (file_buffer,
                                tmp_node->nodename);
			  free (tmp_node->nodename);
			  free (tmp_node);
			}
		    }
		}
	    }
        }

      node = manpage_node_of_file_buffer (file_buffer, pagename);
    }

  return node;
}
