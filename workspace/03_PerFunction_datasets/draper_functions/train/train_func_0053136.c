get_cached(int address) {
	int word_num	= this->word_mul & address;
	int set_num	= (this->set_mul & address)/(this->word_mul + 1);
	int tag_num	= (this->tag_mul & address)/pow(2, this->word_bits + this->set_bits);

	int tag_cap_num	= (this->tag_cap_mul & address)/(this->word_mul + 1);

	Set* cur_set = this->data[set_num];
	for(int i=0; i<assoc; i++) {
		Block* cur_block = cur_set->get_block(i);
		if(cur_block->get_tag() == tag_num) {
			cur_set->inc_counter(cur_block->get_index());
			this->hits++;
			return cur_block->get_word(word_num);
		}
	}

	this->misses[0]++;
	Block* cur_block = this->memory->read(address);

	cur_set->insert_block(tag_num, cur_block);
	if(cur_set->get_dirty()==false) {
		this->misses[1]++;
		cur_set->set_dirty();
	} else {
		this->misses[3]++;
	}

	this->data_cap->insert_block(tag_cap_num, cur_block);
	if(this->data_cap->get_dirty()==false) {
		this->data_cap->set_dirty();
	} else {
		this->misses[2]++;
	}

	return cur_block->get_word(address % this->num_words);
}
