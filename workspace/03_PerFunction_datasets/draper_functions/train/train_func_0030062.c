rm (unsigned char *prefix_, size_t size_)
{
     if (!size_) {
         if (!refcnt)
             return false;
         refcnt--;
         return true;
     }

     unsigned char c = *prefix_;
     if (!count || c < min || c >= min + count)
         return false;

     trie_t *next_node =
         count == 1 ? next.node : next.table [c - min];

     if (!next_node)
         return false;

     bool ret = next_node->rm (prefix_ + 1, size_ - 1);

     if (next_node->is_redundant ()) {
         delete next_node;
         if (count == 1) {
             next.node = 0;
             count = 0;
         }
         else
             next.table [c - min] = 0;
         --live_nodes;
     }

     return ret;
}
