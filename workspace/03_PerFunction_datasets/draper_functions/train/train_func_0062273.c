__glXProcessServerString(const struct extension_info *ext,
                         const char *server_string,
                         unsigned char *server_support)
{
   unsigned base;
   unsigned len;

   for (base = 0; server_string[base] != NUL;  ) {


      for (len = 0; (server_string[base + len] != SEPARATOR)
           && (server_string[base + len] != NUL); len++) {

      }


      set_glx_extension(ext, &server_string[base], len, GL_TRUE,
                        server_support);


      for (base += len; (server_string[base] == SEPARATOR)
           && (server_string[base] != NUL); base++) {

      }
   }
}
