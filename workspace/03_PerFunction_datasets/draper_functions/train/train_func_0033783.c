calculate_total_count_matches(match_counters *counters, match_operation *cur)
{
	size_t result = 0;

	if (!counters) {
		return 0;
	}

	if (counters->match->match->id == cur->id) {
		result = 1;
	}

	if (counters->left) {


		if (cur->id == MATCH_TIMESTAMP) {
			result += (size_t) abs((int) (atol(counters->match->match->value) - atol(counters->left->match->match->value))) - 1;
		}
		result += calculate_total_count_matches(counters->left, cur);
	}
	if (counters->right) {
		if (cur->id == MATCH_TIMESTAMP) {
			result += (size_t) abs((int) (atol(counters->right->match->match->value) - atol(counters->match->match->value))) - 1;
		}
		result += calculate_total_count_matches(counters->right, cur);
	}

	return result;
}
