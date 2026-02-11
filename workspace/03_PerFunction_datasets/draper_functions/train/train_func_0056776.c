write_tree(bc_node *root, FILE *f)
{
   int i;
   if (!root){
      printf("write_tree(): Empty root node!\n");
      return(FUNCTION_TERMINATED_ABNORMALLY);
   }

   write_node(root, f);

   for(i=0; i<root->bobj.child_num; i++){
      write_tree(root->children[i], f);
   }

   return(FUNCTION_TERMINATED_NORMALLY);
}
