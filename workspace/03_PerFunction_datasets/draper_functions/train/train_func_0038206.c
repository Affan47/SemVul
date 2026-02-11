__ecereConstructor___ecereNameSpace__eda__DirFilesDataSourceDriver(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__DirFilesDataSourceDriver * __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver = (struct __ecereNameSpace__eda__DirFilesDataSourceDriver *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DirFilesDataSourceDriver->offset) : 0);

__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__Array_TPL_String_);
__ecereNameSpace__ecere__com__eInstance_IncRef(__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases);
{
struct __ecereNameSpace__ecere__com__Class * c = (struct __ecereNameSpace__ecere__com__Class *)((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class;

__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databaseFileExt = __ecereNameSpace__ecere__com__eClass_GetProperty(c, "databaseFileExtension");
__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->tableFileExt = __ecereNameSpace__ecere__com__eClass_GetProperty(c, "tableFileExtension");
}
return 0x1;
}
