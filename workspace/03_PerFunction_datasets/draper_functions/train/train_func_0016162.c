Linux_Fedora_Version(void)
{
#define FEDORA_ID "Fedora"
#define RELEASE_FLAG "release "


#define FEDORA_REL_FILENAME "/etc/fedora-release"


char relstring[CF_MAXVARSIZE];
char classbuf[CF_MAXVARSIZE];
char *vendor="";
char *release=NULL;
int major = -1;
char strmajor[CF_MAXVARSIZE];

CfOut(cf_verbose,"","This appears to be a fedora system.\n");
NewClass("redhat");
NewClass("fedora");


if (!ReadLine(FEDORA_REL_FILENAME, relstring, sizeof(relstring)))
   {
   return 1;
   }

CfOut(cf_verbose,"","Looking for fedora core linux info...\n");

if (!strncmp(relstring, FEDORA_ID, strlen(FEDORA_ID)))
   {
   vendor = "fedora";
   }
else
   {
   CfOut(cf_verbose,"","Could not identify OS distro from %s\n", FEDORA_REL_FILENAME);
   return 2;
   }


release = strstr(relstring, RELEASE_FLAG);

if (release == NULL)
   {
   CfOut(cf_verbose,"","Could not find a numeric OS release in %s\n",FEDORA_REL_FILENAME);
   return 2;
   }
else
   {
   release += strlen(RELEASE_FLAG);

   if (sscanf(release, "%d", &major) != 0)
      {
      sprintf(strmajor, "%d", major);
      }
   }

if (major != -1 && (strcmp(vendor,"") != 0))
   {
   classbuf[0] = '\0';
   strcat(classbuf, vendor);
   NewClass(classbuf);
   strcat(classbuf, "_");
   strcat(classbuf, strmajor);
   NewClass(classbuf);
   NewScalar("sys","flavour",classbuf,cf_str);
   NewScalar("sys","flavor",classbuf,cf_str);
   }

return 0;
}
