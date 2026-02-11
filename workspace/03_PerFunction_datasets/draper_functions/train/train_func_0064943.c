node_foreach(patricia_node_t* current, int32_t msd, coll_functor_f* functor, void* functor_data) {

	if(current->msd <= msd) {
		return false;
	}
	else {
		void* keyValue[2];
		keyValue[0] = current->key;
		keyValue[1] = current->value;
		bool finished = functor(keyValue, functor_data);
		finished = finished || node_foreach(current->left, current->msd, functor, functor_data);
		finished = finished || node_foreach(current->right, current->msd, functor, functor_data);
		return finished;
	}
}
