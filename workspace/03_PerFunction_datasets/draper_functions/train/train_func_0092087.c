move_file(const GUTF8String &id, int & file_pos,
                         GMap<GUTF8String, void *> & map)


{
   if (!map.contains(id))
   {
      map[id]=0;

      GP<DjVmDir::File> file_rec=djvm_dir->id_to_file(id);
      if (file_rec)
      {
         file_rec=new DjVmDir::File(*file_rec);
         djvm_dir->delete_file(id);
         djvm_dir->insert_file(file_rec, file_pos);

         if (file_pos>=0)
         {
            file_pos++;


            GP<DjVuFile> djvu_file=get_djvu_file(id);
            if (djvu_file)
            {
               GPList<DjVuFile> files_list=djvu_file->get_included_files(false);
               for(GPosition pos=files_list;pos;++pos)
               {
                  const GUTF8String name(files_list[pos]->get_url().fname());
                  GP<DjVmDir::File> child_frec=djvm_dir->name_to_file(name);


                  if (child_frec)
                     if (djvm_dir->get_file_pos(child_frec)>file_pos)
                        move_file(child_frec->get_load_name(), file_pos, map);
               }
            }
         }
      }
   }
}
