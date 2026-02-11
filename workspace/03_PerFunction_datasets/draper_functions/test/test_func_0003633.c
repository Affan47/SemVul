configSelected(int num)
{
   int i;
   if(!((selectedConfig==predefinedConfigNum)&&(num==predefinedConfigNum)))
   {
      selectedConfig = num;
      for(i=0;i<EditNum;i++)
         slider[i]->setEnabled(num==predefinedConfigNum);

      if(num<predefinedConfigNum)
         displayConfig(predefinedConfig[num]);
      else
         displayConfig(config);
      emit changed();
   }
}
