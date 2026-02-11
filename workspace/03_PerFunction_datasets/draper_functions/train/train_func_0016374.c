__ecereMethod_Project_FindNodeByObjectFileName(struct Project * this, char * fileName, int type, unsigned int dotMain, struct ProjectConfig * config)
{
struct ProjectNode * result;
char * cfgName;

if(!config)
config = this->config;
cfgName = config ? config->name : "";
if(!(__extension__ ({
struct __ecereNameSpace__ecere__com__Iterator __internalIterator =
{
this->configsNameCollisions, 0
};

__ecereMethod___ecereNameSpace__ecere__com__Iterator_Index(&__internalIterator, (uint64)(((uint64)(cfgName))), 0x0);
((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&__internalIterator));
})))
ProjectLoadLastBuildNamesInfo(this, config);
result = __ecereMethod_ProjectNode_FindByObjectFileName(this->topNode, fileName, type, dotMain, (__extension__ ({
struct __ecereNameSpace__ecere__com__Iterator __internalIterator =
{
this->configsNameCollisions, 0
};

__ecereMethod___ecereNameSpace__ecere__com__Iterator_Index(&__internalIterator, (uint64)(((uint64)(cfgName))), 0x0);
((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&__internalIterator));
})));
return result;
}
