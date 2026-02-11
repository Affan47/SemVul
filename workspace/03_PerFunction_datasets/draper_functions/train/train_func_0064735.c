rsxx_disable_ier_and_isr(struct rsxx_cardinfo *card,
				  unsigned int intr)
{
	if (unlikely(card->eeh_state))
		return;

	__disable_intr(&card->isr_mask, intr);
	__disable_intr(&card->ier_mask, intr);
	iowrite32(card->ier_mask, card->regmap + IER);
}
