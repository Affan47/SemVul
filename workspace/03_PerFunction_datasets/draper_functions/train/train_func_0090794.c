Linux_Mandrake_Version(void)

{

#define MANDRAKE_ID "Linux Mandrake"
#define MANDRAKE_REV_ID "Mandrake Linux"
#define MANDRAKE_10_1_ID "Mandrakelinux"

#define MANDRAKE_REL_FILENAME "/etc/mandrake-release"

char relstring[CF_MAXVARSIZE];
char *vendor=NULL;

CfOut(cf_verbose,"","This appears to be a mandrake system.\n");
NewClass("Mandrake");

if (!ReadLine(MANDRAKE_REL_FILENAME, relstring, sizeof(relstring)))
   {
   return 1;
   }

CfOut(cf_verbose,"","Looking for Mandrake linux info in \"%s\"\n",relstring);


if(!strncmp(relstring, MANDRAKE_ID, strlen(MANDRAKE_ID)))
   {
   vendor = "mandrake";
   }
else if(!strncmp(relstring, MANDRAKE_REV_ID, strlen(MANDRAKE_REV_ID)))
   {
   vendor = "mandrake";
   }

else if(!strncmp(relstring, MANDRAKE_10_1_ID, strlen(MANDRAKE_10_1_ID)))
   {
   vendor = "mandrake";
   }
else
   {
   CfOut(cf_verbose,"","Could not identify OS distro from %s\n", MANDRAKE_REL_FILENAME);
   return 2;
   }

return Linux_Mandriva_Version_Real(MANDRAKE_REL_FILENAME, relstring, vendor);
}
