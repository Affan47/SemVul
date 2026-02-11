normize(){
    int x,y;
    double sum = 0.0;
    double elems = 0.0;
    for (x = 0;x<size ;x++){
        if (x_description[x]){
            for (y = 0;y<size ;y++){
                if (y!=x && y_description[y]){
                    sum += this->get(x,y);
                    elems += 1.0;
                }
            }
        }
    }
    if (sum == 0.0) return;
    sum /= elems;
    for (x = 0;x<size ;x++){
        for (y = 0;y<size ;y++){
            this->set(x,y,get(x,y)/sum);
        }
    }
}
