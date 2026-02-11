dump_resource(int type, RES *reshdr, void sendit(void *sock, const char *fmt, ...), void *sock)
{
   URES *res = (URES *)reshdr;
   bool recurse = true;

   if (res == NULL) {
      printf(_("No record for %d %s\n"), type, res_to_str(type));
      return;
   }
   if (type < 0) {
      type = - type;
      recurse = false;
   }
   switch (type) {
   case R_DIRECTOR:
      printf(_("Director: name=%s address=%s DIRport=%d\n"), reshdr->name,
              res->dir_res.address, res->dir_res.DIRport);
      break;
   case R_CONSOLE:
      printf(_("Console: name=%s\n"), reshdr->name);
      break;
   case R_CONSOLE_FONT:
      printf(_("ConsoleFont: name=%s font face=%s\n"),
             reshdr->name, NPRT(res->con_font.fontface));
      break;
   default:
      printf(_("Unknown resource type %d\n"), type);
   }
   if (recurse && res->dir_res.hdr.next) {
      dump_resource(type, res->dir_res.hdr.next, sendit, sock);
   }
}
