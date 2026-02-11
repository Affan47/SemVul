chkforgn(outer)
int outer;
   {
   fprintf(codefile, "   if (pfp != (struct p_frame *)");
   if (outer) {
      fprintf(codefile, "&r_frame) {\n");
      fprintf(codefile, "      tend = r_frame.tend.previous;\n");
      }
   else
      fprintf(codefile, "r_pfp) {\n");
   fprintf(codefile, "      return r_signal;\n");
   fprintf(codefile, "      }\n");
   }
