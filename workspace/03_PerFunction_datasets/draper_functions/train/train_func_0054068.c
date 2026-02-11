dup(int start_col,int start_row,
                              int col_count,int row_count)
    {
        Polynomial *ret=new Polynomial(col_count,row_count);

        for(int i=0,c=start_col;i<col_count;i++,c++){
            for(int j=0,r=start_row;j<row_count;j++,r++){
                ret->set(i,j,this->get(c,r));
            }
        }

        return(ret);
    }
