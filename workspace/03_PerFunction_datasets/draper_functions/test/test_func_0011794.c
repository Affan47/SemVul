__ecereMethod___ecereNameSpace__eda__DataSource_Connect(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__DataSource * __ecerePointer___ecereNameSpace__eda__DataSource = (struct __ecereNameSpace__eda__DataSource *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DataSource->offset) : 0);

if(!__ecerePointer___ecereNameSpace__eda__DataSource->locator && __ecerePointer___ecereNameSpace__eda__DataSource->ds)
{
if(__ecerePointer___ecereNameSpace__eda__DataSource->host || __ecerePointer___ecereNameSpace__eda__DataSource->port || __ecerePointer___ecereNameSpace__eda__DataSource->user || __ecerePointer___ecereNameSpace__eda__DataSource->pass)
{
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__eda__DataSource->locator), __ecerePointer___ecereNameSpace__eda__DataSource->locator = 0);
__ecerePointer___ecereNameSpace__eda__DataSource->locator = ((char * (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * ds))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__DataSource->ds;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__DataSourceDriver->_vTbl;
})[__ecereVMethodID___ecereNameSpace__eda__DataSourceDriver_BuildLocator])(__ecerePointer___ecereNameSpace__eda__DataSource->ds, this);
}
}
return __ecerePointer___ecereNameSpace__eda__DataSource->ds ? ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char * locator))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__DataSource->ds;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__DataSourceDriver->_vTbl;
})[__ecereVMethodID___ecereNameSpace__eda__DataSourceDriver_Connect])(__ecerePointer___ecereNameSpace__eda__DataSource->ds, __ecerePointer___ecereNameSpace__eda__DataSource->locator) : 0x0;
}
