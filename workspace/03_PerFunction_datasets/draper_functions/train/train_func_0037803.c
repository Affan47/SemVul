collapsing_find_minlabel(label_t label,
                                 label_t *equivs) {
	int min;
	min = label;
	while (equivs[min] != min)
		min = equivs[min];
	while (label != min) {
		int next = equivs[label];
		equivs[label] = min;
		label = next;
	}
	return min;
}
