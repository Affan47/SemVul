parm_dcl(addr_of, sym)
int addr_of;
struct sym_entry *sym;
   {
   init_ilc();


   just_type(sym->u.declare_var.tqual, 0, 1);
   prt_str(" ", 0);
   ilc_str(" ");


   if (addr_of)
      add_ptr(sym->u.declare_var.dcltor);
   else {
      c_walk(sym->u.declare_var.dcltor, 0, 0);
      ilc_walk(sym->u.declare_var.dcltor, 0, 0);
      }
   prt_str(";", 0);
   ForceNl();
   flush_str();
   return ilc_base.next;
   }
