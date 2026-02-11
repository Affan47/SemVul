__ecereMethod___ecereNameSpace__ecere__sys__GlobalSettings_Close(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__sys__GlobalSettings * __ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings = (struct __ecereNameSpace__ecere__sys__GlobalSettings *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__GlobalSettings->offset) : 0);

if(__ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->f)
{
__ecereMethod___ecereNameSpace__ecere__sys__FileMonitor_StopMonitoring(__ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->settingsMonitor);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 start, uint64 length, unsigned int wait))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Unlock])(__ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->f, 0, 0, 0x1);
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->f), __ecerePointer___ecereNameSpace__ecere__sys__GlobalSettings->f = 0);
}
}
