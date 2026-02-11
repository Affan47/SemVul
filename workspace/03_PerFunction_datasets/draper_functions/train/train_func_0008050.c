SetName(const fstring& _name)
{
	name = FCDEntity::CleanName(_name.c_str());
	SetDirtyFlag();
}
