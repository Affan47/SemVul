ANN_Print(ANNetwork *ann)
{
	printf("============= Start Neural Network =============\n\n");


	printf("n_layers: %u learn_rate: " REAL_NUM_FORMAT " momentum: "REAL_NUM_FORMAT" \n",
						ann->n_layers, ann->learn_rate, ann->momentum);


	printf("n_neurons per layer: ");
	int layer;
	for (layer = 0; layer < ann->n_layers; layer++)
		printf("%u ", ann->n_neurons[layer]);
	printf("\n\n");


	printf("\t\ttheta:\n");
	int neuron, next_neuron;
	for (layer = HIDDEN_START; layer < ann->n_layers; layer++)
	{
		printf("\tlayer %d:\n", layer);
		for (neuron = 0; neuron < ann->n_neurons[layer]; neuron++)
			printf(REAL_NUM_FORMAT" ", ann->theta[layer][neuron]);
		printf("\n");
	}


	printf("\t\tweights:\n");
	for (layer = HIDDEN_START; layer < ann->n_layers; layer++)
	{
		printf("\tlayer %d:\n", layer);
		for (neuron = 0; neuron < ann->n_neurons[layer-1]; neuron++)
			for (next_neuron = 0; next_neuron < ann->n_neurons[layer]; next_neuron++)
				printf("from %d to %d -> "REAL_NUM_FORMAT"\n",
						neuron, next_neuron, ann->weights[layer][neuron][next_neuron]);
	}

	printf("\n");


#ifdef VERBOSE
	printf("\t\toutputs:\n");
	for (layer = HIDDEN_START; layer < ann->n_layers; layer++)
	{
		printf("\tlayer %d:\n", layer);
		for (neuron = 0; neuron < ann->n_neurons[layer]; neuron++)
			printf(REAL_NUM_FORMAT" ", ann->outputs[layer][neuron]);
		printf("\n");
	}
	printf("\n");

	printf("\t\terrors:\n");
	for (layer = HIDDEN_START; layer < ann->n_layers; layer++)
	{
		printf("\tlayer %d:\n", layer);
		for (neuron = 0; neuron < ann->n_neurons[layer]; neuron++)
			printf(REAL_NUM_FORMAT" ", ann->errors[layer][neuron]);
		printf("\n");
	}
	printf("\n");
#endif

	printf("============== End Neural Network ==============\n\n");
}
