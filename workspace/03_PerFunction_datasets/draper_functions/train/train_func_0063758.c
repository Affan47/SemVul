reset_ai_class_names()
{
	ai_class *aicp;

	for (int i = 0; i < Num_ai_classes; i++) {
		aicp = &Ai_classes[i];

		Ai_class_names[i] = aicp->name;
	}
}
