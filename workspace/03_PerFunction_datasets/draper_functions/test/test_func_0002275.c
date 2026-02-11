mlx4_free_irqs(struct mlx4_dev *dev)
{
	struct mlx4_eq_table *eq_table = &mlx4_priv(dev)->eq_table;
	int	i;

	if (eq_table->have_irq)
		free_irq(dev->persist->pdev->irq, dev);

	for (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		if (eq_table->eq[i].have_irq) {
			free_cpumask_var(eq_table->eq[i].affinity_mask);
#if defined(CONFIG_SMP)
			irq_set_affinity_hint(eq_table->eq[i].irq, NULL);
#endif
			free_irq(eq_table->eq[i].irq, eq_table->eq + i);
			eq_table->eq[i].have_irq = 0;
		}

	kfree(eq_table->irq_names);
}
