lock_rec_get_nth_bit(

	const lock_t*	lock,
	ulint		i)
{
	ulint	byte_index;
	ulint	bit_index;

	ut_ad(lock);
	ut_ad(lock_get_type_low(lock) == LOCK_REC);

	if (i >= lock->un_member.rec_lock.n_bits) {

		return(FALSE);
	}

	byte_index = i / 8;
	bit_index = i % 8;

	return(1 & ((const byte*) &lock[1])[byte_index] >> bit_index);
}
