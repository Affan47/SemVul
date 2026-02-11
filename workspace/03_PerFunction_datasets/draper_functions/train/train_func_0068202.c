dht11_handle_irq(int irq, void *data)
{
	struct iio_dev *iio = data;
	struct dht11 *dht11 = iio_priv(iio);


	if (dht11->num_edges < DHT11_EDGES_PER_READ && dht11->num_edges >= 0) {
		dht11->edges[dht11->num_edges].ts = ktime_get_real_ns();
		dht11->edges[dht11->num_edges++].value =
						gpio_get_value(dht11->gpio);

		if (dht11->num_edges >= DHT11_EDGES_PER_READ)
			complete(&dht11->completion);
	}

	return IRQ_HANDLED;
}
