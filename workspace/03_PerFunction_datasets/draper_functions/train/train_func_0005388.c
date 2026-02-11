cdcmd(UAContext *ua, TREE_CTX *tree)
{
   TREE_NODE *node;
   char cwd[2000];


   if (ua->argc != 2) {
      ua->error_msg(_("Too few or too many arguments. Try using double quotes.\n"));
      return 1;
   }
   if (!tree_node_has_child(tree->node)) {
      ua->send_msg(_("Node %s has no children.\n"), tree->node->fname);
      return 1;
   }

   node = tree_cwd(ua->argk[1], tree->root, tree->node);
   if (!node) {

      if (ua->argk[1][1] == ':') {
         bstrncpy(cwd, "/", sizeof(cwd));
         bstrncat(cwd, ua->argk[1], sizeof(cwd));
         node = tree_cwd(cwd, tree->root, tree->node);
      }
      if (!node) {
         ua->warning_msg(_("Invalid path given.\n"));
      } else {
         tree->node = node;
      }
   } else {
      tree->node = node;
   }
   return pwdcmd(ua, tree);
}
