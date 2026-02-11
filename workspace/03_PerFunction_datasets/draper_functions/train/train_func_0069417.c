install(name, flag, argcnt)
char *name;
int flag, argcnt;
   {
   union {
      struct tgentry *gp;
      struct tlentry *lp;
      } p;

   switch (flag) {
      case F_Global:
         if ((p.gp = glookup(name)) == NULL)
            putglob(name, flag, argcnt);
         else
            p.gp->g_flag |= flag;
         break;

      case F_Proc|F_Global:
      case F_Record|F_Global:
      case F_Builtin|F_Global:
         if ((p.gp = glookup(name)) == NULL)
            putglob(name, flag, argcnt);
         else if ((p.gp->g_flag & (~F_Global)) == 0) {


            p.gp->g_flag |= flag;
            p.gp->g_nargs = argcnt;
            }
         else
            tfatal("inconsistent redeclaration", name);
         break;

      case F_Static:
      case F_Dynamic:
      case F_Argument:
         if ((p.lp = llookup(name)) == NULL)
            putloc(name,flag);
         else if (p.lp->l_flag == flag)
            tfatal("redeclared identifier", name);
         else
            tfatal("inconsistent redeclaration", name);
         break;

      default:
         tsyserr("install: unrecognized symbol table flag.");
      }
   }
