__ecereProp_ProjectNode_IsSet_options(struct ProjectNode * this)
{
struct __ecereNameSpace__ecere__com__Instance * options = this->project ? __ecereProp_Project_Get_options(this->project) : this->options;

return options && !__ecereProp_ProjectOptions_Get_isEmpty(options);
}
