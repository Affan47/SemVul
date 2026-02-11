rds_instance_out (rds_model, name)
     rdsfig_list *rds_model;
     char *name;
{
   rdsins_list *pt;

   name = namealloc (name);

   for (pt = rds_model->INSTANCE; pt; pt = pt->NEXT)
      if (pt->INSNAME == name)
         return pt;
   return NULL;
}
