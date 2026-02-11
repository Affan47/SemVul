_new_app_check_item(Evry_Action *act __UNUSED__, const Evry_Item *it)
{
   GET_APP(app, it);

   if (app->desktop)
     return 1;

   if (app->file && strlen(app->file) > 0)
     return 1;

   return 0;
}
