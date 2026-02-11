RemoveNode(Node *n)
{
   RemoveRoute(n);
   for(int i=0; i<search.count(); i++) {
      if(search[i]->best_node==n)
	 search.remove(i--);
   }
   if(n->requests_in_flight>0) {
      for(const Request *r=sent_req.each_begin(); r; r=sent_req.each_next()) {
	 if(r->node_id.eq(n->id))
	    sent_req.remove(sent_req.each_key());
      }
   }
   node_by_addr.remove(n->addr.compact());
   nodes.remove(n->id);
}
