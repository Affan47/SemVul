operator() ( const RefTokenWithIndex& t ) {
			out << "[txt='" << t->getText() << "' tp=" << t->getType() << " idx=" << t->getIndex() << "]\n";
		}
