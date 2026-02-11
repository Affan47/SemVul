draw(Canvas* c, const Allocation& a) const {
    if (state_->test(TelltaleState::is_chosen)) {
	info().shadow1()->draw(c, a);
	info().shadow2()->draw(c, a);
	info().checkmark()->draw(c, a);
    }
}
