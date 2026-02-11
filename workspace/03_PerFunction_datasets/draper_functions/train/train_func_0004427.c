__ecereMethod_ProjectNode_GetMatchingNodeConfig(struct ProjectNode * this, struct ProjectConfig * prjConfig)
{
struct ProjectConfig * nodeConfig = (((void *)0));

if(__ecereProp_ProjectNode_Get_configurations(this) && prjConfig)
{
const char * configName = prjConfig->name;

{
struct __ecereNameSpace__ecere__com__Iterator cfg =
{
__ecereProp_ProjectNode_Get_configurations(this), 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&cfg))
{
if(!(strcasecmp)(((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&cfg))->name, configName))
{
nodeConfig = ((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&cfg));
break;
}
}
}
}
return nodeConfig;
}
