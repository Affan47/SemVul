uv_get_irq_domain(void)
{
	static struct irq_domain *uv_domain;
	static DEFINE_MUTEX(uv_lock);

	mutex_lock(&uv_lock);
	if (uv_domain == NULL) {
		uv_domain = irq_domain_add_tree(NULL, &uv_domain_ops, NULL);
		if (uv_domain)
			uv_domain->parent = x86_vector_domain;
	}
	mutex_unlock(&uv_lock);

	return uv_domain;
}
