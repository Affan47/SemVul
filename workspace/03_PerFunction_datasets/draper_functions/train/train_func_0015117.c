setup_payload_interference(struct ra_graph *g,
                                         int first_payload_node,
                                         int reg_node_count)
{
   int payload_node_count = this->first_non_payload_grf;

   for (int i = 0; i < payload_node_count; i++) {


      ra_set_node_reg(g, first_payload_node + i, i);


      for (int j = 0; j < reg_node_count; j++) {
         ra_add_node_interference(g, first_payload_node + i, j);
      }
   }
}
