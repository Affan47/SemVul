getResult()
{
   ASCString result = "#fontsize=16#Memory Footprint\n#fontsize=12#all sizes in kB\n\n";
   result += root.prettyPrint(0);

   result += "#indent=0,0#";

   result += "\n\n#fontsize=16#Objects#fontsize=12#\n\n";


   result += for_each ( objectTypeRepository.getVector().begin(), objectTypeRepository.getVector().end(), ObjectStorage<ObjectType*>() ).print();
   return result;
}
