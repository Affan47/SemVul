fncout(head, prm_dcl, block)
struct node *head;
struct node *prm_dcl;
struct node *block;
   {
   if (!enable_out)
      return;

   def_fnd = 1;

   nxt_sbuf = 0;
   nxt_cbuf = 0;


   fnc_head = head;
   c_walk(head, 0, 0);
   prt_str(" ",  0);
   c_walk(prm_dcl, 0, 0);
   prt_str(" ", 0);


   prt_tok(block->tok, IndentInc);
   c_walk(block->u[0].child, IndentInc, 0);
   spcl_dcls(NULL);
   no_ret_val = 1;
   c_walk(block->u[2].child, IndentInc, 0);
   if (ntend != 0 && no_ret_val) {


      untend(IndentInc);
      }
   ForceNl();
   prt_str("}", IndentInc);
   ForceNl();


   free_tree(head);
   free_tree(prm_dcl);
   free_tree(block);
   pop_cntxt();
   clr_def();
   }
