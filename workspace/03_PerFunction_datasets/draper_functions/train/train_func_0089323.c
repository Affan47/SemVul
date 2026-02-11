Restart()
{
   ip_voted.empty();
   ip_votes.empty();
   routes.truncate();

   for(Node *n=nodes.each_begin(); n; n=nodes.each_next()) {
      if(n->IsGood())
	 AddRoute(n);
   }
}
