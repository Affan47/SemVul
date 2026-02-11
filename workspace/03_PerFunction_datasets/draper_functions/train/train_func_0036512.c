new_by_layer(Layer layer)
{
	if(layer < LAYER_FILE)
		return new StreamEncoder(layer);
	else
		return new FileEncoder(layer);
}
