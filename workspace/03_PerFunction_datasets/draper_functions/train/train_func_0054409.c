StripTrailingNewline(char *str)

{ char *c = str + strlen(str);

if (c - str > CF_EXPANDSIZE)
   {
   CfOut(cf_error, "", "StripTrailingNewline was called on an overlong string");
   return;
   }

for (; c >= str && (*c == '\0' || *c == '\n'); --c)
   {
   *c = '\0';
   }
}
