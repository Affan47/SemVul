sortBody() {
	if (!hasWeights()) {
		std::sort(goals_, goals_+posSize_);
		std::sort(goals_+posSize_, goals_+size());
	}
	else {
		WeightLitVec temp;
		temp.reserve(size());
		for (uint32 i = 0; i != size(); ++i) {
			temp.push_back(WeightLiteral(goal(i), weight(i)));
		}
		std::sort(temp.begin(), temp.begin()+posSize());
		std::sort(temp.begin()+posSize(), temp.end());
		for (uint32 i = 0; i != size(); ++i) {
			goals_[i]              = temp[i].first;
			extra_.ext->weights[i] = temp[i].second;
		}
	}
}
