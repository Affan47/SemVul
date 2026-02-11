Analyze() const throw(semantic::Error) {

  if(this->oper == OP_DIVIDE) {
    const std::shared_ptr<Node> rhs = this->GetChild(1);
    const std::shared_ptr<Constant> c =
      std::dynamic_pointer_cast<Constant>(rhs);
    if(c->GetValue() == 0.0) {
      throw semantic::DivisionByZero("Cannot divide by zero.", __FILE__,
                                     __LINE__);
    }
  }
}
