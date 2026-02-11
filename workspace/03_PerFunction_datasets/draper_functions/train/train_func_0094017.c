__ecereProp_LicenseTab_Set_sourceFile(struct __ecereNameSpace__ecere__com__Instance * this, char *  value)
{
struct LicenseTab * __ecerePointer_LicenseTab = (struct LicenseTab *)(this ? (((char *)this) + __ecereClass_LicenseTab->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * f = __ecereFunction___ecereNameSpace__ecere__sys__FileOpen(value, 1);

if(f)
{
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Load(__ecerePointer_LicenseTab->editBox, f);
(__ecereNameSpace__ecere__com__eInstance_DecRef(f), f = 0);
}
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp_LicenseTab_sourceFile), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM_LicenseTab_sourceFile);
}
