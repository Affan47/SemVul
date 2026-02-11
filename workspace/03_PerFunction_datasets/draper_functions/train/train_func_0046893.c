desired_offset(short level, double ftHt)
{
   if(level > 0){
      return -level * ftHt * pow(0.6, abs(level));
   }
   else if(level < 0){
      return level * ftHt * pow(0.6, abs(level));
   }
   else{
      return 0;
   }
}
