ScheduleLinkOperation(char *destination,char *source,struct Attributes attr,struct Promise *pp)

{
const char *lastnode;

lastnode = ReadLastNode(destination);

if (MatchRlistItem(attr.link.copy_patterns,lastnode))
   {
   CfOut(cf_verbose,""," -> Link %s matches copy_patterns\n",destination);
   VerifyCopy(attr.link.source,destination,attr,pp);
   return true;
   }

switch (attr.link.link_type)
   {
   case cfa_symlink:
       VerifyLink(destination,source,attr,pp);
       break;
   case cfa_hardlink:
       VerifyHardLink(destination,source,attr,pp);
       break;
   case cfa_relative:
       VerifyRelativeLink(destination,source,attr,pp);
       break;
   case cfa_absolute:
       VerifyAbsoluteLink(destination,source,attr,pp);
       break;
   default:
       CfOut(cf_error,"","Unknown link type - should not happen.\n");
       break;
   }

return true;
}
