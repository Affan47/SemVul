Nodes(const char* const * target_prop_whitelist ,
	size_t whitelist_size ) const
{
	AnimationCurveNodeList nodes;


	const std::vector<const Connection*>& conns = doc.GetConnectionsByDestinationSequenced(ID(),"AnimationCurveNode");
	nodes.reserve(conns.size());

	BOOST_FOREACH(const Connection* con, conns) {


		if (con->PropertyName().length()) {
			continue;
		}

		const Object* const ob = con->SourceObject();
		if(!ob) {
			DOMWarning("failed to read source object for AnimationCurveNode->AnimationLayer link, ignoring",&element);
			continue;
		}

		const AnimationCurveNode* const anim = dynamic_cast<const AnimationCurveNode*>(ob);
		if(!anim) {
			DOMWarning("source object for ->AnimationLayer link is not an AnimationCurveNode",&element);
			continue;
		}

		if(target_prop_whitelist) {
			const char* s = anim->TargetProperty().c_str();
			bool ok = false;
			for (size_t i = 0; i < whitelist_size; ++i) {
				if (!strcmp(s, target_prop_whitelist[i])) {
					ok = true;
					break;
				}
			}
			if(!ok) {
				continue;
			}
		}
		nodes.push_back(anim);
	}

	return nodes;
}
