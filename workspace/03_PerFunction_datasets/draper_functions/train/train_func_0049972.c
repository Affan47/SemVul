delete_file(const GUTF8String &id)
{
   DEBUG_MSG("Deleting file with id='" << (const char *)id << "'\n");
   DEBUG_MAKE_INDENT(3);

   GCriticalSectionLock lock((GCriticalSection *) &class_lock);

   for(GPosition pos=files_list;pos;++pos)
   {
      GP<File> & f=files_list[pos];
      if (id == f->id)
      {
         name2file.del(f->name);
         id2file.del(f->id);
         title2file.del(f->title);
         if (f->is_page())
         {
            for(int page=0;page<page2file.size();page++)
            {
               if (page2file[page]==f)
               {
                  int i;
                  for(i=page;i<page2file.size()-1;i++)
                     page2file[i]=page2file[i+1];
                  page2file.resize(page2file.size()-2);
                  for(i=page;i<page2file.size();i++)
                     page2file[i]->page_num=i;
                  break;
               }
            }
         }
         files_list.del(pos);
         break;
      }
   }
}
