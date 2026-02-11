find_slot(int client, int port)
{
	int i;
	struct seq_oss_midi *mdev;
	unsigned long flags;

	spin_lock_irqsave(&register_lock, flags);
	for (i = 0; i < max_midi_devs; i++) {
		mdev = midi_devs[i];
		if (mdev && mdev->client == client && mdev->port == port) {

			snd_use_lock_use(&mdev->use_lock);
			spin_unlock_irqrestore(&register_lock, flags);
			return mdev;
		}
	}
	spin_unlock_irqrestore(&register_lock, flags);
	return NULL;
}
