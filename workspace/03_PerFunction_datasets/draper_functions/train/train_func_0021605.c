getBalanceSecure(std::string pinHash, std::string bankSecret){
    if( this->validatePin( pinHash, bankSecret ) ){
        return this->getBalance();
    }
    else{
        return -1;
    }
}
