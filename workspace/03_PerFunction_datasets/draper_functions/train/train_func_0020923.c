updateSaveName()
{

	if (m_old_states.isEmpty()) {
		return;
	}
	QList<int> keys = m_old_states.keys();
	qSort(keys);
	int count = keys.count();


	int steps = m_text->document()->availableUndoSteps();
	int nearest_smaller = 0;
	int nearest_larger = count - 1;
	for (int i = 0; i < count; ++i) {
		if (keys.at(i) <= steps) {
			nearest_smaller = i;
		}
		if (keys.at(i) >= steps) {
			nearest_larger = i;
			break;
		}
	}


	for (int i = nearest_smaller; i > -1; --i) {
		QPair<QString, bool>& state = m_old_states[keys.at(i)];
		if (state.second == m_rich_text) {
			state.first = m_filename;
		} else {
			break;
		}
	}
	for (int i = nearest_larger; i < count; ++i) {
		QPair<QString, bool>& state = m_old_states[keys.at(i)];
		if (state.second == m_rich_text) {
			state.first = m_filename;
		} else {
			break;
		}
	}
}
