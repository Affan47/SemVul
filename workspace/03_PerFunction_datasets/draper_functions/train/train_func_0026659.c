ClassBanner(enum typesequence type)

{ struct Item *ip;
  int i;

if (type != kp_interfaces)
   {
   return;
   }

CfOut(cf_verbose,"","\n");
CfOut(cf_verbose,"","     +  Private classes augmented:\n");

for (i = 0; i < CF_ALPHABETSIZE; i++)
   {
   for (ip = VADDCLASSES.list[i]; ip != NULL; ip=ip->next)
      {
      CfOut(cf_verbose,"","     +       %s\n",ip->name);
      }
   }

CfOut(cf_verbose,"","\n");

CfOut(cf_verbose,"","     -  Private classes diminished:\n");

for (ip = VNEGHEAP; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,"","     -       %s\n",ip->name);
   }

CfOut(cf_verbose,"","\n");

Debug("     ?  Public class context:\n");

for (i = 0; i < CF_ALPHABETSIZE; i++)
   {
   for (ip = VHEAP.list[i]; ip != NULL; ip=ip->next)
      {
      Debug("     ?       %s\n",ip->name);
      }
   }

CfOut(cf_verbose,"","\n");
}
