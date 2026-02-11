_print_current_dir(Evas_Object *obj)
{
   Elm_Ctxpopup_Direction dir;
   dir = elm_ctxpopup_direction_get(obj);

   switch(dir)
     {
      case ELM_CTXPOPUP_DIRECTION_LEFT:
         printf("ctxpopup direction: left!\n");
         break;
      case ELM_CTXPOPUP_DIRECTION_RIGHT:
         printf("ctxpopup direction: right!\n");
         break;
      case ELM_CTXPOPUP_DIRECTION_UP:
         printf("ctxpopup direction: up!\n");
         break;
      case ELM_CTXPOPUP_DIRECTION_DOWN:
         printf("ctxpopup direction: down!\n");
         break;
      case ELM_CTXPOPUP_DIRECTION_UNKNOWN:
         printf("ctxpopup direction: unknow!\n");
         break;
     }
}
