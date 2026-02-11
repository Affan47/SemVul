sortBoundables(const BoundableList* input)
{
	std::auto_ptr<BoundableList> output ( new BoundableList(*input) );
	sort(output->begin(), output->end(), compareSIRBoundables);

	return output;
}

}
