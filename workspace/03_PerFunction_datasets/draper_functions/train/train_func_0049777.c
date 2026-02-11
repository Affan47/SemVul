_pci_find_saved_cap(struct pci_dev *pci_dev,
						       u16 cap, bool extended)
{
	struct pci_cap_saved_state *tmp;

	hlist_for_each_entry(tmp, &pci_dev->saved_cap_space, next) {
		if (tmp->cap.cap_extended == extended && tmp->cap.cap_nr == cap)
			return tmp;
	}
	return NULL;
}
