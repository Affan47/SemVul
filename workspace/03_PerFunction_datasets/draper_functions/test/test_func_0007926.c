Walk(GenericWalkingCallback callback, void* user_data) const
{
	if(!callback)	return false;

	struct Local
	{
		static void _Walk(const AABBQuantizedNode* current_node, GenericWalkingCallback callback, void* user_data)
		{
			if(!current_node || !(callback)(current_node, user_data))	return;

			if(!current_node->IsLeaf())
			{
				_Walk(current_node->GetPos(), callback, user_data);
				_Walk(current_node->GetNeg(), callback, user_data);
			}
		}
	};
	Local::_Walk(mNodes, callback, user_data);
	return true;
}
