make_undirected() {
   if(is_undirected())
      return;
   std::vector<smallEdge*> remove;
   {
      EdgePtrIterator *it = get_edges();
      Edge* e;
      while((e = it->next()) != NULL) {
         Node* from = e->from_node;
         Node* to = e->to_node;
         e->is_directed = false;
         if(has_edge(to,from)) {
            remove.push_back(new smallEdge(to, from));
         }
      }

      delete it;
   }
   for(std::vector<smallEdge*>::iterator it = remove.begin();
         it != remove.end(); it++) {
      try {
         remove_edge((*it)->_from, (*it)->_to);
      }
      catch (std::runtime_error) {
         std::cerr << "somthing went wrong" << std::endl;
      }
      delete *it;
   }
   GRAPH_UNSET_FLAG(this, FLAG_DIRECTED);
}
