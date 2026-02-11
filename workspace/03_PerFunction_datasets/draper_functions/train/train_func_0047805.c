print_cmd_index()
{
   int i=0;
   const cmd_rec *cmd_table=dyn_cmd_table?dyn_cmd_table.get():static_cmd_table;
   const int count=dyn_cmd_table?dyn_cmd_table.count():static_cmd_table_length;
   int width=fd_width(1);
   int pos=0;
   const int align=37;
   const int first_align=4;
   while(i<count)
   {
      while(i<count && !cmd_table[i].short_desc)
	 i++;
      if(i>=count)
	 break;
      const char *c1=gettext(cmd_table[i].short_desc);
      i++;
      int w1=mbswidth(c1,0);

      int pad=0;
      if(pos<first_align)
	 pad=first_align-pos;
      else if(pos>first_align)
	 pad=align-(pos-first_align)%align;
      if(pos>first_align && pos+pad+w1>=width) {
	 printf("\n");
	 pos=0;
	 pad=first_align;
      }

      printf("%*s%s",pad,"",c1);
      pos+=pad+w1;
   }
   if(pos>0)
      printf("\n");
}
