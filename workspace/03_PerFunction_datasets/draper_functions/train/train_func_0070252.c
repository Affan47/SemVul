save_resource(int type, RES_ITEM *items, int pass)
{
   URES *res;
   int rindex = type - r_first;
   int i, size;
   int error = 0;


   for (i=0; items[i].name; i++) {
      if (items[i].flags & ITEM_REQUIRED) {
            if (!bit_is_set(i, res_all.res_dir.hdr.item_present)) {
               Emsg2(M_ABORT, 0, _("%s item is required in %s resource, but not found.\n"),
                 items[i].name, resources[rindex]);
             }
      }
   }


   if (pass == 2) {
      switch (type) {

         case R_CONSOLE:
         case R_DIRECTOR:
            break;

         default:
            Emsg1(M_ERROR, 0, _("Unknown resource type %d\n"), type);
            error = 1;
            break;
      }


      if (res_all.res_dir.hdr.name) {
         free(res_all.res_dir.hdr.name);
         res_all.res_dir.hdr.name = NULL;
      }
      if (res_all.res_dir.hdr.desc) {
         free(res_all.res_dir.hdr.desc);
         res_all.res_dir.hdr.desc = NULL;
      }
      return;
   }


   switch (type) {
   case R_CONSOLE:
      size = sizeof(CONRES);
      break;
   case R_DIRECTOR:
      size = sizeof(DIRRES);
      break;
   default:
      printf(_("Unknown resource type %d\n"), type);
      error = 1;
      size = 1;
      break;
   }

   if (!error) {
      res = (URES *)malloc(size);
      memcpy(res, &res_all, size);
      if (!res_head[rindex]) {
         res_head[rindex] = (RES *)res;
      } else {
         RES *next, *last;
         for (last=next=res_head[rindex]; next; next=next->next) {
            last = next;
            if (strcmp(next->name, res->res_dir.hdr.name) == 0) {
               Emsg2(M_ERROR_TERM, 0,
                  _("Attempt to define second %s resource named \"%s\" is not permitted.\n"),
                  resources[rindex].name, res->res_dir.hdr.name);
            }
         }
         last->next = (RES *)res;
         Dmsg2(90, "Inserting %s res: %s\n", res_to_str(type),
               res->res_dir.hdr.name);
      }
   }
}
